defmodule LookingGlass.Consumer do
  use GenServer
  use AMQP
  require Logger

  def start_link(_opts) do
    GenServer.start_link(__MODULE__, [], [])
  end

  @exchange "test_queue"
  @queue "test_queue"
  @queue_error "#{@queue}_error"
  @topic "debugger"

  def init(_opts) do
    {:ok, conn} = Connection.open("amqp://guest:guest@localhost")
    {:ok, chan} = Channel.open(conn)
    setup_queue(chan)

    # Limit unacknowledged messages to 10
    :ok = Basic.qos(chan, prefetch_count: 10)
    # Register the GenServer process as a consumer
    {:ok, _consumer_tag} = Basic.consume(chan, @queue)
    {:ok, %{id: 0, chan: chan}}
  end

  def subscribe do
    Logger.error("subscribed")
    Phoenix.PubSub.subscribe(LookingGlass.PubSub, @topic)
  end

  # Confirmation sent by the broker after registering this process as a consumer
  def handle_info(
        {:basic_consume_ok, %{consumer_tag: _consumer_tag}},
        state
      ) do
    {:noreply, state}
  end

  # Sent by the broker when the consumer is unexpectedly cancelled (such as after a queue deletion)
  def handle_info({:basic_cancel, %{consumer_tag: _consumer_tag}}, state) do
    {:stop, :normal, state}
  end

  # Confirmation sent by the broker to the consumer process after a Basic.cancel
  def handle_info(
        {:basic_cancel_ok, %{consumer_tag: _consumer_tag}},
        state
      ) do
    {:noreply, state}
  end

  def handle_info(
        {:basic_deliver, payload, %{delivery_tag: tag, redelivered: redelivered}},
        %{id: id, chan: chan} = _state
      ) do
    # You might want to run payload consumption in separate Tasks in production
    with {:ok, %{"event" => event, "result" => result}} <-
           consume(chan, tag, redelivered, payload) do
      #   Logger.warn(result)

      broadcast(event, %{id: id, result: result})
      {:noreply, %{id: id + 1, chan: chan}}
    else
      _err ->
        {:noreply, %{id: id, chan: chan}}
    end
  end

  defp broadcast(event, result) do
    # Logger.error("broadcast")
    Logger.info(event)
    Logger.info(result)
    Phoenix.PubSub.broadcast(LookingGlass.PubSub, @topic, {event, result})
  end

  defp setup_queue(chan) do
    {:ok, _} = Queue.declare(chan, @queue_error, durable: true)

    # Messages that cannot be delivered to any consumer in the main queue will be routed to the error queue
    {:ok, _} =
      Queue.declare(chan, @queue,
        durable: true,
        arguments: [
          {"x-dead-letter-exchange", :longstr, ""},
          {"x-dead-letter-routing-key", :longstr, @queue_error}
        ]
      )

    :ok = Exchange.fanout(chan, @exchange, durable: true)
    :ok = Queue.bind(chan, @queue, @exchange)
  end

  defp consume(channel, tag, redelivered, payload) do
    {:ok, event} = Jason.decode(payload)
    Basic.ack(channel, tag)
    {:ok, event}
  rescue
    # Requeue unless it's a redelivered message.
    # This means we will retry consuming a message once in case of exception
    # before we give up and have it moved to the error queue
    #
    # You might also want to catch :exit signal in production code.
    # Make sure you call ack, nack or reject otherwise comsumer will stop
    # receiving messages.
    exception ->
      :ok = Basic.reject(channel, tag, requeue: not redelivered)
      Logger.error("Error converting #{payload}")
      {:error, %{}}
  end
end

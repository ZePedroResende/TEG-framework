defmodule Live.Subscriber do
  use GenServer

  def start_link(topic) do
    GenServer.start_link(__MODULE__, topic, name: __MODULE__)
  end

  def init(topic) do
    {:ok, socket} = :chumak.socket(:sub)
    :chumak.subscribe(socket, topic)
    send(self(), :bind)
    {:ok, %{socket: socket}}
  end

  def handle_info(:bind, %{socket: socket} = state) do
    {:ok, _pid} = :chumak.connect(socket, :tcp, 'localhost', 8082)
    send(self(), :recv)
    {:noreply, state}
  end

  def handle_info(:recv, %{socket: socket} = state) do
    IO.inspect("hello")
    {:ok, data} = :chumak.recv(socket)
    IO.inspect(data)
    send(self(), :recv)
    {:noreply, state}
  end
end

defmodule LookingGlassWeb.DebuggerLive do
  use LookingGlassWeb, :live_view
  alias LookingGlass.Consumer
  require Logger

  @impl true
  def mount(_params, _session, socket) do
    if connected?(socket), do: Consumer.subscribe()

    socket =
      assign(socket,
        nodes: %{},
        e: []
      )

    {:ok, socket}
  end

  def handle_info({"nodes", nodes}, socket) do
    {:noreply, assign(socket, :nodes, nodes)}
  end

  def handle_info({"enqueue", events}, socket) do
    {:noreply, push_event(socket, "enqueue", events)}
    # {:noreply, assign(socket, :e, updated_events)}
  end

  def handle_info({"calculate", events}, socket) do
    {:noreply, push_event(socket, "calculate", events)}
    # {:noreply, assign(socket, :e, updated_events)}
  end

  def handle_info({"result", events}, socket) do
    {:noreply, push_event(socket, "result", events)}
    # {:noreply, assign(socket, :e, updated_events)}
  end

  def handle_info({"finish", events}, socket) do
    {:noreply, push_event(socket, "finish", events)}
    # {:noreply, assign(socket, :e, updated_events)}
  end
end

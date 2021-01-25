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

  def handle_info({"update", events}, socket) do
    updated_events = Enum.concat(socket.assigns.e, [events])
    {:noreply, assign(socket, :e, updated_events)}
  end
end

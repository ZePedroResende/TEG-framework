# This file is responsible for configuring your application
# and its dependencies with the aid of the Mix.Config module.
#
# This configuration file is loaded before any dependency and
# is restricted to this project.

# General application configuration
use Mix.Config

config :looking_glass,
  ecto_repos: [LookingGlass.Repo]

# Configures the endpoint
config :looking_glass, LookingGlassWeb.Endpoint,
  url: [host: "localhost"],
  secret_key_base: "QkNLbjgqFYTP7hNU+i26waQfg2u745UmjrCYlDp8M7uDbgsdVaygsoS74XgZicO3",
  render_errors: [view: LookingGlassWeb.ErrorView, accepts: ~w(html json), layout: false],
  pubsub_server: LookingGlass.PubSub,
  live_view: [signing_salt: "kyGrsjGn"]

# Configures Elixir's Logger
config :logger, :console,
  format: "$time $metadata[$level] $message\n",
  metadata: [:request_id]

# Use Jason for JSON parsing in Phoenix
config :phoenix, :json_library, Jason

# Import environment specific config. This must remain at the bottom
# of this file so it overrides the configuration defined above.
import_config "#{Mix.env()}.exs"

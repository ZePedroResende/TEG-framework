defmodule LookingGlass.Repo do
  use Ecto.Repo,
    otp_app: :looking_glass,
    adapter: Ecto.Adapters.Postgres
end

process :example_worker do

  # Only action this process in production on a specific host
  # constraint :environment => 'production', :host => 'app01.myapp.com'

  # Only action this process in development
  # constraint :environment => 'development'

  # Define the action to be carried out when this process should start
  start do
    system("#{root}/scripts/omxp.sh &")
    system("sleep 2; #{root}/scripts/genius.sh &")
  end

  # Define the action to be carried out when this process should stop
  stop do
    system("#{root}/scripts/dbus.sh stop;");
    system("kill -9 $(pgrep omxplayer)");
    system("kill -9 $(pgrep genius.sh )");
  end

  # Define the action to be carried out when this process should restart
  restart do
    stop
    start
  end


end

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ServerManager.Bll
{
    public class PluginDataProvider
    {
        //Start a thread, listening for new data. Raise event, when new data is available

        public event EventHandler<NewDataEventArgs> NewDataEvent;

        private Thread ListenerThread;
        private ConnectionProvider _connectionProvider;
        
        private bool _started;
        public bool Started
        {
            get { return _started; }
            private set { _started = value; }
        }


        public PluginDataProvider()
        {
            this._connectionProvider = new ConnectionProvider();
        }

        public void StartListener()
        {
            this.ListenerThread = new Thread(this.ListenerRun);
            this.Started = true;
            this.ListenerThread.Start();

            Console.WriteLine("Listener starting");
        }

        public void StopListener()
        {
            Task.Factory.StartNew(() =>
            {
                //Try to stop the thread normal:
                this.Started = false;
                this.ListenerThread.Join(500);

                //if it fails, kill it:
                if (this.ListenerThread.IsAlive)
                {
                    this.ListenerThread.Abort();
                }

                Console.WriteLine("Listener stopped");
            });

        }

        private void ListenerRun()
        {
            Console.Out.WriteLine("Listener started!");
            while (this.Started)
            {
                Console.Out.WriteLine("Listening ...");
                int sleepTime = 1000;
                var data = this._connectionProvider.ReadData();

                if (data != null && data != String.Empty)
                {
                    Console.Out.WriteLine("Handling new data");
                    //Do something

                    var args = new NewDataEventArgs();
                    args.Data = data;
                    
                    this.OnNewData(this, args);

                    sleepTime += 2000;
                }
                else
                {
                    Console.WriteLine("No Data present");
                    sleepTime += 1000;
                }

                Console.Out.WriteLine("Thead sleep");
                Thread.Sleep(sleepTime);
            }

        }

        private void OnNewData(Object sender, NewDataEventArgs args)
        {
            NewDataEvent(sender, args);
        }
    }
}

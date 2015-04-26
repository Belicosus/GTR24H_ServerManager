using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ServerManager.Bll
{
    class PluginDataProvider
    {
        //Start a thread, listening for new data. Raise event, when new data is available

        public event EventHandler<EventArgs> NewDataEvent;

        private Thread ListenerThread;

        public PluginDataProvider()
        {
            
        }

        public void StartListener()
        {
            this.ListenerThread = new Thread(this.ListenerRun);
            this.ListenerThread.Start();
        }

        private void ListenerRun()
        {
            //Task.Factory.StartNew(() =>
            //{

            //});




        }

    }
}

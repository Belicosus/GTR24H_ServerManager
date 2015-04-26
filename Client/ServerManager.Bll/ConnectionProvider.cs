using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ServerManager.Bll
{
    public class ConnectionProvider
    {

        private string strData;

        public string ReadData()
        {
            Thread.Sleep(10);
            if (strData == string.Empty)
            {
                strData = "Player 1;Ferrari";
                
            }
            else
            {
                strData = String.Empty;
            }

            return strData;
        }

        public void SendCommand(string command)
        {
            
        }

    }
}

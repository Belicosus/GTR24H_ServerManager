using System;

namespace ServerManager.Bll
{
    public enum DataType
    {
        ScoringList,
        CarInfo,
    }

    public class NewDataEventArgs : EventArgs
    {
        public string Data { get; set; }    
        public DataType Type { get; set; }
    }
}
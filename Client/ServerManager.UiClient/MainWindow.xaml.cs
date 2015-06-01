using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ServerManager.Bll;

namespace ServerManager.UiClient
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private PluginDataProvider _pluginDataProvider;

        public MainWindow()
        {
            InitializeComponent();

            //This is a debug console:
            ConsoleManager.Show();
            Console.WriteLine("This is the debug console!");

            //Initialize reading thread:
            this._pluginDataProvider = new PluginDataProvider();
            this._pluginDataProvider.NewDataEvent += this.NewDataEventHandler;
            this._pluginDataProvider.StartListener();
            
            this.Closing += this.WindowClosingEventHandler;
        }

        private void WindowClosingEventHandler(object sender, CancelEventArgs e)
        {
            this._pluginDataProvider.StopListener();
        }

        private void NewDataEventHandler(object sender, NewDataEventArgs e)
        {
            



        }
    }
}

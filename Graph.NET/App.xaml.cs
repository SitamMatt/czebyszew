using LiveCharts;
using LiveCharts.Defaults;
using LiveCharts.Wpf;
using Microsoft.VisualBasic.FileIO;
using PowerArgs;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Globalization;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace Graph.NET
{
    /// <summary>
    /// Logika interakcji dla klasy App.xaml
    /// </summary>
    public partial class App : Application
    {
        void App_Startup(object sender, StartupEventArgs e)
        {
            MainWindow mainWindow = new MainWindow();
            ChartValues<ObservablePoint> Functions = new ChartValues<ObservablePoint>();
            ChartValues<ObservablePoint> Interpolated = new ChartValues<ObservablePoint>();
            ChartValues<ObservablePoint> Nodes = new ChartValues<ObservablePoint>();


            var args = Args.Parse<FileArgs>(e.Args);


            using (TextFieldParser parser = new TextFieldParser(args.Function)) {
                var series = new ChartValues<ObservablePoint>();
                parser.TextFieldType = FieldType.Delimited;
                parser.SetDelimiters(" ");
                while (!parser.EndOfData)
                {
                    string[] fields = parser.ReadFields();
                    double x = double.Parse(fields[0], CultureInfo.InvariantCulture);
                    double y = double.Parse(fields[1], CultureInfo.InvariantCulture);
                    series.Add(new ObservablePoint(x, y));
                }
                Functions = series;
            };
            using (TextFieldParser parser = new TextFieldParser(args.Interpolated))
            {
                var series = new ChartValues<ObservablePoint>();
                parser.TextFieldType = FieldType.Delimited;
                parser.SetDelimiters(" ");
                while (!parser.EndOfData)
                {
                    string[] fields = parser.ReadFields();
                    double x = double.Parse(fields[0], CultureInfo.InvariantCulture);
                    double y = double.Parse(fields[1], CultureInfo.InvariantCulture);
                    series.Add(new ObservablePoint(x, y));
                }
                Interpolated = series;
            };
            using (TextFieldParser parser = new TextFieldParser(args.Nodes))
            {
                var series = new ChartValues<ObservablePoint>();
                parser.TextFieldType = FieldType.Delimited;
                parser.SetDelimiters(" ");
                while (!parser.EndOfData)
                {
                    string[] fields = parser.ReadFields();
                    double x = double.Parse(fields[0], CultureInfo.InvariantCulture);
                    double y = double.Parse(fields[1], CultureInfo.InvariantCulture);
                    series.Add(new ObservablePoint(x, y));
                }
                Nodes = series;
            };

            mainWindow.Chart.FunValues.AddRange(Functions);
            mainWindow.Chart.InterpolatedValues.AddRange(Interpolated);
            mainWindow.Chart.NodesValues.AddRange(Nodes);
            //mainWindow.Chart.Values = series;
            mainWindow.Show();
            mainWindow.Chart.Update();

        }
    }
}

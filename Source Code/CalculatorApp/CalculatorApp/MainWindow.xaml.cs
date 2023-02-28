using System;
using System.Collections.Generic;
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

namespace CalculatorApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        int firstNumber;
        int secondNumber;
        int total;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void CalculateAdd(object sender, RoutedEventArgs e)
        {
            firstNumber = Convert.ToInt32(numA.Text);
            secondNumber = Convert.ToInt32(numB.Text);

            total = firstNumber + secondNumber;

            result.Content = total.ToString();
        }

        private void CalculateSubtract(object sender, RoutedEventArgs e)
        {
            firstNumber = Convert.ToInt32(numA.Text);
            secondNumber = Convert.ToInt32(numB.Text);

            total = firstNumber - secondNumber;

            result.Content = total.ToString();
        }

        private void CalculateMultiply(object sender, RoutedEventArgs e)
        {
            firstNumber = Convert.ToInt32(numA.Text);
            secondNumber = Convert.ToInt32(numB.Text);

            total = firstNumber * secondNumber;

            result.Content = total.ToString();
        }

        private void CalculateDivide(object sender, RoutedEventArgs e)
        {
            firstNumber = Convert.ToInt32(numA.Text);
            secondNumber = Convert.ToInt32(numB.Text);

            double total = (double)firstNumber / secondNumber;

            result.Content = total.ToString("#.##");
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace PGWPF
{
    public class MainWindowViewModel : BindableBase
    {
        public MainWindowViewModel()
        {
            ;
        }

        public class SphereGenerationCommandImpl : ICommand
        {
            public event EventHandler CanExecuteChanged
            {
                add { }
                remove { }
            }

            public bool CanExecute(object parameter)
            {
                return true;
            }

            public void Execute(object parameter)
            {
                ;
            }
        }

    }
}

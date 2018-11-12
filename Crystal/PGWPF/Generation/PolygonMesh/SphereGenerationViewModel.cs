using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace PG.CGStudio.Generation
{
    public class SphereGenerationViewModel : BindableBase
    {
        private int unum;
        private int vnum;

        public int UNum
        {
            get { return unum; }
            set { this.SetProperty(ref unum, value); }
        }

        public int VNum
        {
            get { return vnum; }
            set { this.SetProperty(ref vnum, value); }
        }

        public class ExecuteCommandImpl : ICommand
        {
            private SphereGenerationViewModel viewModel;

            public ExecuteCommandImpl(SphereGenerationViewModel vm)
            {
                this.viewModel = vm;
            }

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

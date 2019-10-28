using Reactive.Bindings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PG.CGStudio.Selection
{
    public class RegionSelectViewModel
    {
        public ReactiveCommand OkCommand { get; }
            = new ReactiveCommand();

        public RegionSelectViewModel()
        {
            OkCommand.Subscribe(OnOk);
        }

        private void OnOk()
        {
            
        }
    }
}

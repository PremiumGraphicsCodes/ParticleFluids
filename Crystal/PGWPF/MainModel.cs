using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PG.CLI;

namespace PG.CGStudio
{
    public class MainModel
    {
        private Model model;

        static MainModel instance;

        public static MainModel Instance { get { return instance; } }

        public MainModel()
        {
            model = new Model();
            instance = this;
        }
    }
}

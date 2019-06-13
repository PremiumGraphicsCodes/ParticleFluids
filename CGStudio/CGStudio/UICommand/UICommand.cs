using PG.CGStudio.UICtrl;

namespace PG.CGStudio.UICommand
{
    public abstract class UICommand : IUICtrl
    {
        public UICommand()
        {}

        public abstract bool IsCompleted();
    }
}

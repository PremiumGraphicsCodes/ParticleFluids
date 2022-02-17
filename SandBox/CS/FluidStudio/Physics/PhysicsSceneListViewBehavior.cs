﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interactivity;

namespace FluidStudio.Physics
{
    public class PhysicsSceneListViewBehavior : Behavior<TreeView>
    {
        protected override void OnAttached()
        {
            this.AssociatedObject.MouseDoubleClick += this.ItemDoubleClicked;
            this.AssociatedObject.KeyDown += this.KeyDowned;
        }

        protected override void OnDetaching()
        {
            this.AssociatedObject.MouseDoubleClick -= this.ItemDoubleClicked;
            this.AssociatedObject.KeyDown -= this.KeyDowned;
        }

        private void KeyDowned(object sender, KeyEventArgs e)
        {
            var treeView = e.Source as TreeView;
            if (treeView == null)
            {
                return;
            }
            if (e.Key == Key.Delete)
            {
                var item = treeView.SelectedItem as PhysicsSceneViewModel;
                var solver = item.Model.Parent as SolverScene;
                if (solver != null)
                {
                    solver.Delete(item.Model);
                }
            }
        }

        private void ItemDoubleClicked(object sender, MouseButtonEventArgs e)
        {
            var view = sender as TreeView;
            var treeView = e.Source as TreeView;
            if (treeView == null)
            {
                return;
            }
            var viewModel = treeView.DataContext as PhysicsSceneListViewModel;
            var selectedItem = treeView.SelectedItem as PhysicsSceneViewModel;
            var physicsScene = selectedItem.Model;
            viewModel.ChangeView(physicsScene);
            //            viewModel.ChangeView(selectedItem);
        }
    }
}
﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PG.Core.Math;

namespace PG.CGStudio.UICtrl
{
    public class ObjectPickUICtrl : IUICtrl
    {
        public override void OnLeftButtonDown(Vector2d position)
        {
            var id = Canvas3dView.Instance.Renderer.Pick(position);
            if(id.parentId != 0)
            {
                ;
            }
        }
    }
}

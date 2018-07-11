﻿namespace TaskMgr.Ctls
{
    partial class PerformanceCpu
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.performanceInfos = new TaskMgr.Ctls.PerformanceInfos();
            this.performanceGridGlobal = new TaskMgr.Ctls.PerformanceGrid();
            this.performanceTitle = new TaskMgr.Ctls.PerformanceTitle();
            this.SuspendLayout();
            // 
            // performanceInfos
            // 
            this.performanceInfos.ColorText = System.Drawing.Color.Black;
            this.performanceInfos.ColorTitle = System.Drawing.Color.Gray;
            this.performanceInfos.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.performanceInfos.FontText = new System.Drawing.Font("微软雅黑", 12F);
            this.performanceInfos.FontTextSpeical = new System.Drawing.Font("微软雅黑", 15F);
            this.performanceInfos.FontTitle = new System.Drawing.Font("微软雅黑", 9F);
            this.performanceInfos.Location = new System.Drawing.Point(0, 277);
            this.performanceInfos.MaxSpeicalItemsWidth = 200;
            this.performanceInfos.Name = "performanceInfos";
            this.performanceInfos.Size = new System.Drawing.Size(586, 161);
            this.performanceInfos.TabIndex = 2;
            // 
            // performanceGridGlobal
            // 
            this.performanceGridGlobal.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.performanceGridGlobal.BgColor = System.Drawing.Color.FromArgb(((int)(((byte)(241)))), ((int)(((byte)(246)))), ((int)(((byte)(250)))));
            this.performanceGridGlobal.BottomTextHeight = 20;
            this.performanceGridGlobal.DrawColor = System.Drawing.Color.FromArgb(((int)(((byte)(17)))), ((int)(((byte)(125)))), ((int)(((byte)(187)))));
            this.performanceGridGlobal.GridColor = System.Drawing.Color.FromArgb(((int)(((byte)(206)))), ((int)(((byte)(226)))), ((int)(((byte)(240)))));
            this.performanceGridGlobal.LeftBottomText = "60 秒";
            this.performanceGridGlobal.LeftText = "% 利用率";
            this.performanceGridGlobal.Location = new System.Drawing.Point(3, 45);
            this.performanceGridGlobal.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.performanceGridGlobal.Name = "performanceGridGlobal";
            this.performanceGridGlobal.RightBottomText = "0";
            this.performanceGridGlobal.RightText = "100 %";
            this.performanceGridGlobal.Size = new System.Drawing.Size(580, 225);
            this.performanceGridGlobal.TabIndex = 0;
            this.performanceGridGlobal.TopTextHeight = 20;
            // 
            // performanceTitle
            // 
            this.performanceTitle.Dock = System.Windows.Forms.DockStyle.Top;
            this.performanceTitle.Location = new System.Drawing.Point(0, 0);
            this.performanceTitle.Name = "performanceTitle";
            this.performanceTitle.Size = new System.Drawing.Size(586, 38);
            this.performanceTitle.SmallTitle = "cpu id and name";
            this.performanceTitle.SmallTitleFont = new System.Drawing.Font("微软雅黑", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.performanceTitle.TabIndex = 1;
            this.performanceTitle.Title = "CPU";
            this.performanceTitle.TitleFont = new System.Drawing.Font("微软雅黑", 21.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            // 
            // PerformanceCpu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.Controls.Add(this.performanceInfos);
            this.Controls.Add(this.performanceGridGlobal);
            this.Controls.Add(this.performanceTitle);
            this.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Margin = new System.Windows.Forms.Padding(10);
            this.Name = "PerformanceCpu";
            this.Size = new System.Drawing.Size(586, 438);
            this.ResumeLayout(false);

        }

        #endregion
        public PerformanceGrid performanceGridGlobal;
        public PerformanceTitle performanceTitle;
        public PerformanceInfos performanceInfos;
    }
}

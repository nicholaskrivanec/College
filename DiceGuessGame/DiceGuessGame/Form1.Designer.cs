namespace DiceGuessGame
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.diceImage = new System.Windows.Forms.PictureBox();
            this.RollButton = new System.Windows.Forms.Button();
            this.ResetButton = new System.Windows.Forms.Button();
            this.statsBox = new System.Windows.Forms.RichTextBox();
            this.GameInfoGroupBox = new System.Windows.Forms.GroupBox();
            this.amtLost = new System.Windows.Forms.Label();
            this.amtWon = new System.Windows.Forms.Label();
            this.amtPlayed = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.TextBox1 = new System.Windows.Forms.TextBox();
            this.guessLabel = new System.Windows.Forms.Label();
            this.errorMessage = new System.Windows.Forms.Label();
            this.noInputMessage = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.diceImage)).BeginInit();
            this.GameInfoGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // diceImage
            // 
            this.diceImage.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.diceImage.Image = global::DiceGuessGame.Properties.Resources.die6;
            this.diceImage.InitialImage = null;
            this.diceImage.Location = new System.Drawing.Point(51, 218);
            this.diceImage.Name = "diceImage";
            this.diceImage.Size = new System.Drawing.Size(76, 71);
            this.diceImage.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.diceImage.TabIndex = 0;
            this.diceImage.TabStop = false;
            // 
            // RollButton
            // 
            this.RollButton.Location = new System.Drawing.Point(180, 218);
            this.RollButton.Name = "RollButton";
            this.RollButton.Size = new System.Drawing.Size(75, 23);
            this.RollButton.TabIndex = 1;
            this.RollButton.Text = "Roll";
            this.RollButton.UseVisualStyleBackColor = true;
            this.RollButton.Click += new System.EventHandler(this.RollButton_Click);
            // 
            // ResetButton
            // 
            this.ResetButton.Location = new System.Drawing.Point(180, 266);
            this.ResetButton.Name = "ResetButton";
            this.ResetButton.Size = new System.Drawing.Size(75, 23);
            this.ResetButton.TabIndex = 2;
            this.ResetButton.Text = "Reset";
            this.ResetButton.UseVisualStyleBackColor = true;
            this.ResetButton.Click += new System.EventHandler(this.ResetButton_Click);
            // 
            // statsBox
            // 
            this.statsBox.BackColor = System.Drawing.SystemColors.Window;
            this.statsBox.Location = new System.Drawing.Point(13, 315);
            this.statsBox.Name = "statsBox";
            this.statsBox.ReadOnly = true;
            this.statsBox.Size = new System.Drawing.Size(389, 105);
            this.statsBox.TabIndex = 3;
            this.statsBox.Text = resources.GetString("statsBox.Text");
            // 
            // GameInfoGroupBox
            // 
            this.GameInfoGroupBox.Controls.Add(this.amtLost);
            this.GameInfoGroupBox.Controls.Add(this.amtWon);
            this.GameInfoGroupBox.Controls.Add(this.amtPlayed);
            this.GameInfoGroupBox.Controls.Add(this.label3);
            this.GameInfoGroupBox.Controls.Add(this.label2);
            this.GameInfoGroupBox.Controls.Add(this.label1);
            this.GameInfoGroupBox.Location = new System.Drawing.Point(16, 12);
            this.GameInfoGroupBox.Name = "GameInfoGroupBox";
            this.GameInfoGroupBox.Size = new System.Drawing.Size(239, 143);
            this.GameInfoGroupBox.TabIndex = 4;
            this.GameInfoGroupBox.TabStop = false;
            this.GameInfoGroupBox.Text = "Game Info";
            // 
            // amtLost
            // 
            this.amtLost.AutoSize = true;
            this.amtLost.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.amtLost.Location = new System.Drawing.Point(203, 107);
            this.amtLost.Name = "amtLost";
            this.amtLost.Size = new System.Drawing.Size(16, 16);
            this.amtLost.TabIndex = 5;
            this.amtLost.Text = "0";
            // 
            // amtWon
            // 
            this.amtWon.AutoSize = true;
            this.amtWon.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.amtWon.Location = new System.Drawing.Point(203, 63);
            this.amtWon.Name = "amtWon";
            this.amtWon.Size = new System.Drawing.Size(16, 16);
            this.amtWon.TabIndex = 4;
            this.amtWon.Text = "0";
            // 
            // amtPlayed
            // 
            this.amtPlayed.AutoSize = true;
            this.amtPlayed.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.amtPlayed.Location = new System.Drawing.Point(203, 20);
            this.amtPlayed.Name = "amtPlayed";
            this.amtPlayed.Size = new System.Drawing.Size(16, 16);
            this.amtPlayed.TabIndex = 3;
            this.amtPlayed.Text = "0";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(10, 107);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(163, 16);
            this.label3.TabIndex = 2;
            this.label3.Text = "Number of Times Lost:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(10, 63);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(165, 16);
            this.label2.TabIndex = 1;
            this.label2.Text = "Number of Times Won:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(7, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(183, 16);
            this.label1.TabIndex = 0;
            this.label1.Text = "Number of Times Played:";
            // 
            // TextBox1
            // 
            this.TextBox1.Location = new System.Drawing.Point(192, 175);
            this.TextBox1.MaxLength = 1;
            this.TextBox1.Name = "TextBox1";
            this.TextBox1.Size = new System.Drawing.Size(29, 20);
            this.TextBox1.TabIndex = 5;
            this.TextBox1.TextChanged += new System.EventHandler(this.TextBox1_TextChanged);
            this.TextBox1.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TextBox1_KeyPress);
            // 
            // guessLabel
            // 
            this.guessLabel.AutoSize = true;
            this.guessLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guessLabel.Location = new System.Drawing.Point(23, 179);
            this.guessLabel.Name = "guessLabel";
            this.guessLabel.Size = new System.Drawing.Size(163, 16);
            this.guessLabel.TabIndex = 6;
            this.guessLabel.Text = "Enter your guess (1-6):";
            // 
            // errorMessage
            // 
            this.errorMessage.AutoSize = true;
            this.errorMessage.BackColor = System.Drawing.SystemColors.Info;
            this.errorMessage.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.errorMessage.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.errorMessage.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.errorMessage.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.errorMessage.Location = new System.Drawing.Point(227, 181);
            this.errorMessage.Name = "errorMessage";
            this.errorMessage.Size = new System.Drawing.Size(207, 15);
            this.errorMessage.TabIndex = 7;
            this.errorMessage.Text = "Only numbers 1 through 6 are valid";
            this.errorMessage.TextAlign = System.Drawing.ContentAlignment.TopRight;
            this.errorMessage.Visible = false;
            // 
            // noInputMessage
            // 
            this.noInputMessage.AutoSize = true;
            this.noInputMessage.BackColor = System.Drawing.SystemColors.Info;
            this.noInputMessage.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.noInputMessage.ForeColor = System.Drawing.SystemColors.Highlight;
            this.noInputMessage.Location = new System.Drawing.Point(227, 168);
            this.noInputMessage.Name = "noInputMessage";
            this.noInputMessage.Size = new System.Drawing.Size(166, 13);
            this.noInputMessage.TabIndex = 8;
            this.noInputMessage.Text = "<-Enter a guess before Roll.";
            this.noInputMessage.Visible = false;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(293, 218);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(109, 71);
            this.button1.TabIndex = 9;
            this.button1.Text = "Prove the Law of Large Numbers";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(444, 446);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.noInputMessage);
            this.Controls.Add(this.errorMessage);
            this.Controls.Add(this.guessLabel);
            this.Controls.Add(this.TextBox1);
            this.Controls.Add(this.GameInfoGroupBox);
            this.Controls.Add(this.statsBox);
            this.Controls.Add(this.ResetButton);
            this.Controls.Add(this.RollButton);
            this.Controls.Add(this.diceImage);
            this.Name = "Form1";
            this.Text = "Die Guess Game";
            this.Enter += new System.EventHandler(this.RollButton_Click);
            ((System.ComponentModel.ISupportInitialize)(this.diceImage)).EndInit();
            this.GameInfoGroupBox.ResumeLayout(false);
            this.GameInfoGroupBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox diceImage;
        private System.Windows.Forms.Button RollButton;
        private System.Windows.Forms.Button ResetButton;
        private System.Windows.Forms.RichTextBox statsBox;
        private System.Windows.Forms.GroupBox GameInfoGroupBox;
        private System.Windows.Forms.TextBox TextBox1;
        private System.Windows.Forms.Label guessLabel;
        private System.Windows.Forms.Label errorMessage;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label amtLost;
        private System.Windows.Forms.Label amtWon;
        private System.Windows.Forms.Label amtPlayed;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label noInputMessage;
        private System.Windows.Forms.Button button1;
    }
}


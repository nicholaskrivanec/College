using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DiceGuessGame
{
    public partial class Form1 : Form
    {
        #region Attributes:
        // constants to define array sizes
        public const int NUM_DICE = 6; // represents the number of dice face values
        public const int NUM_ROWS = 7; // number of rows in the statBox
        public const int NUM_COLS = 4; // number of columns in the statBox

        // stores the user's guess (1-6) and the dice roll value
        private int guess;
        private int randomInt;

        // to get random dice roll:
        private Random iRandom = new Random();

        // boolean shows if guess is valid input
        private bool isValid;

        // amount of Wins, and losses; appearing in the Game Info box: timesPlayed is the their sum
        private int iTimesWon;
        private int iTimesLost;
        private int iTimesPlayed;

        // Each Column's data going in the statBox
        private int[] iArrFrequency;
        private double[] dArrPercent;
        private int[] iArrGuesses;

        // spacing before columns in table
        private const string sFaceSpace = "   ";
        private const string sFreqSpace = "        ";
        private const string sPercSpace = "    ";

        // tabs after columns in stat table
        private const string sFaceTab = "\t";
        private const string sFreqTab = "\t\t";
        private const string sPercTab = "\t\t\t";

        // 2D array to hold stat string values to go in stat rich textbox
        private string[,] statTable;

        // define the column names as constants
        private const int FACE = 0;
        private const int FREQ = 1;
        private const int PERC = 2;
        private const int GUES = 3;
        #endregion

        #region methods:
        /// <summary>
        /// Initializes Component along with most variables.
        /// </summary>
        public Form1()
        {
            InitializeComponent();
            iTimesWon = 0;
            iTimesLost = 0;
            iTimesPlayed = 0;
            isValid = false;
            iArrFrequency = new int[NUM_DICE] { 0, 0, 0, 0, 0, 0 };
            dArrPercent = new double[NUM_DICE] { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00 };
            iArrGuesses = new int[NUM_DICE] { 0, 0, 0, 0, 0, 0 };

            // initialize the stat table
            statTable = new string[NUM_ROWS, NUM_COLS]
            {
                //spaces before value, tabs after
                {"FACE\t",         "FREQUENCY\t",       "PERCENT\t",    "NUMBER OF GUESSES\n" },
                {sFaceSpace+"1"+sFaceTab, sFreqSpace+"0"+sFreqTab, sPercSpace+"0.00%"+sPercTab, "0\n" },
                {sFaceSpace+"2"+sFaceTab, sFreqSpace+"0"+sFreqTab, sPercSpace+"0.00%"+sPercTab, "0\n" },
                {sFaceSpace+"3"+sFaceTab, sFreqSpace+"0"+sFreqTab, sPercSpace+"0.00%"+sPercTab, "0\n" },
                {sFaceSpace+"4"+sFaceTab, sFreqSpace+"0"+sFreqTab, sPercSpace+"0.00%"+sPercTab, "0\n" },
                {sFaceSpace+"5"+sFaceTab, sFreqSpace+"0"+sFreqTab, sPercSpace+"0.00%"+sPercTab, "0\n" },
                {sFaceSpace+"6"+sFaceTab, sFreqSpace+"0"+sFreqTab, sPercSpace+"0.00%"+sPercTab, "0" }
            };

        }

        /// <summary>
        /// Changes the dice image using random int when RollButton is clicked
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RollButton_Click(object sender, EventArgs e)
        {
            // hide all error messages
            HideErrorMessage();
            HideInputNeededMessage();

            // if they haven't entered a guess, display enter guess error message
            if (TextBox1.Text == "")
            {
                ShowInputNeededMessage();
                return;
            }
            
            // if input is invalid show message and return
            if (isValid == false)
            {
                ShowErrorMessage();
                return;
            }

            //AnimateDice();                                                              // simulate the dice roll
            randomInt = iRandom.Next(1, 7);                                             // store the random int
            diceImage.Image = Image.FromFile("die" + randomInt.ToString() + ".gif");    // retrieve the new Dice image file using random int
            diceImage.Refresh();                                                        // refresh the dice image

            UpdateValues(guess, randomInt);    // update attribute values
            UpdateGameInfo();                  // update the game info box
            UpdateGameStatsBox();              // update the game stats textbox
        }

        /// <summary>
        /// updates all game values: wins, losses, etc...; does NOT change displays of value
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        private void UpdateValues(int iGuess, int iRandom)
        {
            // if guess is the same as dice roll, timesWon++, else timesLost++
            if (iGuess == iRandom)
            {
                iTimesWon++;
            }
            else
            {
                iTimesLost++;
            }
     
            // increment Number of Guesses and update statTable    
            iArrGuesses[iGuess - 1]++;
            statTable[iGuess, GUES] = iArrGuesses[iGuess - 1].ToString();

            // if guess was not 6 then add a newline at the number guessed
            if (iGuess != 6)
            {
                statTable[iGuess, GUES] += '\n';
            }

            // increment roll Frequency and update statTable
            iArrFrequency[iRandom - 1]++;
            statTable[iRandom, FREQ] = sFreqSpace + iArrFrequency[iRandom - 1].ToString()+sFreqTab;

            iTimesPlayed = iTimesWon + iTimesLost;

            // update the percentages using frequency/timesplayed
            for (int i = 0; i < NUM_DICE; i++)
            {
                // update the actual percentage doubles, then the stat table
                dArrPercent[i] = (double)iArrFrequency[i] / iTimesPlayed;
                statTable[i + 1, PERC] = sPercSpace + dArrPercent[i].ToString("P");

                // if percentage is 100 percent, only 2 tabs after, else 3 tabs
                if (dArrPercent[i] == 1)   statTable[i + 1, PERC] += "\t\t";
                else                            statTable[i + 1, PERC] += "\t\t\t";

            }
        }

        /// <summary>
        /// updates the game Info box text info
        /// </summary>
        private void UpdateGameInfo()
        {
            // display updated results in Game Info box
            amtPlayed.Text = iTimesPlayed.ToString();
            amtWon.Text = iTimesWon.ToString();
            amtLost.Text = iTimesLost.ToString();
        }

        /// <summary>
        /// updates the game stats in bottome rich text box
        /// </summary>
        private void UpdateGameStatsBox()
        {
            statsBox.Text = "";
            for (int i = 0; i < NUM_ROWS; i++)
            {
                for(int j=0; j< NUM_COLS; j++)
                {
                    statsBox.Text += statTable[i, j];
                }
            }
        }

        /// <summary>
        /// simulates a dice roll 
        /// </summary>
        private void AnimateDice()
        {
            for (int i = 0; i < 10; i++)
            {
                // change the dice image randomly 10 times
                diceImage.Image = Image.FromFile("die" + iRandom.Next(1, 7).ToString() + ".gif");

                // slow down image change time so the change is visible to the user
                Thread.Sleep(75);

                // refresh the image;
                diceImage.Refresh();
            }
        }

        /// <summary>
        /// Gets the guess from the textbox, stores it in guess var
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TextBox1_TextChanged(object sender, EventArgs e)
        {
            // if entry is a num inclusively between 1 and 6, it's valid, hide error message.
            if (Int32.TryParse(TextBox1.Text, out guess) && (guess > 0 && guess < 7))
            {
                isValid = true;
                HideErrorMessage();
                return;
            }

            // if theres nothing in the textbox return
            if (TextBox1.Text == "") { return; }
            
            // otherwise show error message
            isValid = false;
            ShowErrorMessage();
        }

        /// <summary>
        /// hides the error message from user interface
        /// </summary>
        private void HideErrorMessage()
        {
            errorMessage.Visible = false;
        }

        /// <summary>
        /// displays the error message for invalid input
        /// </summary>
        private void ShowErrorMessage()
        {
            errorMessage.Visible = true;
        }

        /// <summary>
        /// Shows the input needed message for when user tries to roll without entering a guess
        /// </summary>
        private void ShowInputNeededMessage()
        {
            noInputMessage.Visible = true;
        }

        /// <summary>
        /// Hides Input needed message if user makes a guess
        /// </summary>
        private void HideInputNeededMessage()
        {
            noInputMessage.Visible = false;
        }

        /// <summary>
        /// Resets all game stats, labels, and textboxes
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ResetButton_Click(object sender, EventArgs e) 
        {
            //set all attributes to 0 or empty
            iTimesWon = 0;
            iTimesLost = 0;
            iTimesPlayed = 0;

            //set all array values to 0
            for (int i = 0; i < NUM_DICE; i++)
            {
                iArrFrequency[i] = 0;
                iArrGuesses[i] = 0;
                dArrPercent[i] = 0.00;
            }

            //reset statTable multiArr
            statTable = new string[NUM_ROWS, NUM_COLS]
            {
                //spaces before value, tabs after
                {"FACE\t",         "FREQUENCY\t",       "PERCENT\t",    "NUMBER OF GUESSES\n" },
                {sFaceSpace+"1"+sFaceTab, sFreqSpace+"0"+sFreqTab, sPercSpace+"0.00%"+sPercTab, "0\n" },
                {sFaceSpace+"2"+sFaceTab, sFreqSpace+"0"+sFreqTab, sPercSpace+"0.00%"+sPercTab, "0\n" },
                {sFaceSpace+"3"+sFaceTab, sFreqSpace+"0"+sFreqTab, sPercSpace+"0.00%"+sPercTab, "0\n" },
                {sFaceSpace+"4"+sFaceTab, sFreqSpace+"0"+sFreqTab, sPercSpace+"0.00%"+sPercTab, "0\n" },
                {sFaceSpace+"5"+sFaceTab, sFreqSpace+"0"+sFreqTab, sPercSpace+"0.00%"+sPercTab, "0\n" },
                {sFaceSpace+"6"+sFaceTab, sFreqSpace+"0"+sFreqTab, sPercSpace+"0.00%"+sPercTab, "0" }
            };

            // hide all error messages
            HideErrorMessage();
            HideInputNeededMessage();

            // empty the guess box
            TextBox1.Text = null;

            // update gameinfo display, and statBox display
            UpdateGameStatsBox();
            UpdateGameInfo();

            // reset the dice image to image 6
            diceImage.Image = Image.FromFile("die6.gif");

            // reset the statBox rtextbox
            UpdateGameStatsBox();
            
        }
        #endregion

        /// <summary>
        /// if enter key is pressed while cursor is in the textBox1, the roll_button is activated
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void TextBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            // found this code on stack overflow to make it easier (ie I don't like using a mouse)
            //https://stackoverflow.com/questions/12318164/enter-key-press-in-c-sharp
            if (e.KeyChar == Convert.ToChar(Keys.Enter))
            {
                RollButton_Click(sender, e);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < 10000; i++)
            {
                RollButton_Click(sender, e);
            }
        }
    }
}

using System;
using System.Drawing;
using System.Windows.Forms;

namespace ChessGame
{
    public partial class ChessGame : Form
    {
        private const int BOARD_SIZE = 8;
        private const int PIECE_SIZE = 64;
        private const int BORDER_SIZE = 2;

        private PictureBox[,] _pictureBoxes;
        private Point[,] _startingPositions;

        public ChessGame()
        {
            InitializeComponent();
            Initialize();
        }



        public void Initialize()
        {
            _pictureBoxes = new PictureBox[BOARD_SIZE, BOARD_SIZE];
            _startingPositions = new Point[BOARD_SIZE, BOARD_SIZE];

            // Initialize starting positions
            for (int row = 0; row < BOARD_SIZE; row++)
            {
                for (int col = 0; col < BOARD_SIZE; col++)
                {
                    int adjustedRow = row;
                    int adjustedCol = col;

                    if (row >= BOARD_SIZE / 2)
                    {
                        adjustedRow = BOARD_SIZE - row - 1;
                        adjustedCol = BOARD_SIZE - col - 1;
                    }

                    _startingPositions[row, col] = new Point(adjustedCol * PIECE_SIZE, adjustedRow * PIECE_SIZE);
                }
            }

            // Set padding of table layout panel to zero
            tableLayoutPanel1.Padding = new Padding(0);

            // Draw chess board
            DrawChessBoard();

            // Draw chess pieces
            DrawChessPieces();
        }





        private void DrawChessBoard()
        {
            int squareSize = tableLayoutPanel1.Width / BOARD_SIZE;

            for (int row = 0; row < BOARD_SIZE; row++)
            {
                for (int col = 0; col < BOARD_SIZE; col++)
                {
                    // get existing picture box from array
                    PictureBox pictureBox = _pictureBoxes[row, col];

                    // set properties of picture box
                    pictureBox.Size = new Size(PIECE_SIZE, PIECE_SIZE);
                    pictureBox.BackColor = GetCellColor(row, col);
                    pictureBox.SizeMode = PictureBoxSizeMode.StretchImage;
                    pictureBox.BackColor = Color.Transparent; // set background color to transparent

                    // attach OnMouseClick event to the picture box
                    pictureBox.MouseClick += PictureBox_OnMouseClick;
                }
            }
        }

        private void DrawChessPieces()
        {
            for (int row = 0; row < BOARD_SIZE; row++)
            {
                for (int col = 0; col < BOARD_SIZE; col++)
                {
                    // get image for chess piece
                    Image chessPieceImage = GetChessPieceImage(row, col);

                    // update image of picture box, if chess piece image is not null
                    if (chessPieceImage != null)
                    {
                        // get existing picture box from array
                        PictureBox pictureBox = _pictureBoxes[row, col];

                        // set properties of picture box
                        pictureBox.Image = chessPieceImage;
                        pictureBox.SizeMode = PictureBoxSizeMode.CenterImage;

                        // calculate location of picture box
                        int x = col * PIECE_SIZE + BORDER_SIZE;
                        int y = row * PIECE_SIZE + BORDER_SIZE;
                        pictureBox.Location = new Point(x, y);
                    }
                }
            }
        }


        private Image GetChessPieceImage(int row, int col)
        {
            string pieceName = GetPieceName(row, col);

            switch (pieceName)
            {
                case "Rook":
                    return Chess.Properties.Resources.Rook;
                case "Knight":
                    return Chess.Properties.Resources.Knight;
                case "Bishop":
                    return Chess.Properties.Resources.Bishop;
                case "Queen":
                    return Chess.Properties.Resources.Queen;
                case "King":
                    return Chess.Properties.Resources.King;
                case "Pawn":
                    return Chess.Properties.Resources.Pawn;
                case "Pawn2":
                    return Chess.Properties.Resources.Pawn2;
                case "Rook2":
                    return Chess.Properties.Resources.Rook2;
                case "Knight2":
                    return Chess.Properties.Resources.Knight2;
                case "Bishop2":
                    return Chess.Properties.Resources.Bishop2;
                case "Queen2":
                    return Chess.Properties.Resources.Queen2;
                case "King2":
                    return Chess.Properties.Resources.King2;
                default:
                    return null;
            }
        }


        private string GetPieceName(int row, int col)
{
    switch (row)
    {
        case 0:
            switch (col)
            {
                case 0:
                case 7:
                    return "Rook2"; // black rook
                case 1:
                case 6:
                    return "Knight2"; // black knight
                case 2:
                case 5:
                    return "Bishop2"; // black bishop
                case 3:
                    return "Queen2"; // black queen
                case 4:
                    return "King2"; // black king
            }
            break;
        case 1:
            return "Pawn2"; // black pawn
        case 6:
            return "Pawn"; // white pawn
        case 7:
            switch (col)
            {
                case 0:
                case 7:
                    return "Rook"; // white rook
                case 1:
                case 6:
                    return "Knight"; // white knight
                case 2:
                case 5:
                    return "Bishop"; // white bishop
                case 3:
                    return "Queen"; // white queen
                case 4:
                    return "King"; // white king
            }
            break;
    }

    return null;
}






        private Color GetCellColor(int row, int col)
        {
            if ((row + col) % 2 == 0)
            {
                return Color.White;
            }
            else
            {
                // Check if the current cell contains a black or white piece based on its starting position
                if (row == 0 || row == 1 || row == 6 || row == 7)
                {
                    if (col % 2 == 0)
                    {
                        // Cell contains a black piece
                        return Color.LightGray;
                    }
                    else
                    {
                        // Cell contains a white piece
                        return Color.White;
                    }
                }
                else
                {
                    // Cell is empty
                    return Color.LightGray;
                }
            }
        }

        private void PictureBox_OnMouseClick(object sender, MouseEventArgs e)
        {
            PictureBox pictureBox = sender as PictureBox;
            int row = tableLayoutPanel1.GetRow(pictureBox);
            int col = tableLayoutPanel1.GetColumn(pictureBox);
            ChessLocation clickedLocation = new ChessLocation(row, col);

            // TODO: Handle the click event for the picture box at the clicked location
        }


        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {
            int cellSize = tableLayoutPanel1.Width / BOARD_SIZE;

            using (SolidBrush whiteBrush = new SolidBrush(Color.White))
            using (SolidBrush blackBrush = new SolidBrush(Color.Gray))
            {
                for (int row = 0; row < BOARD_SIZE; row++)
                {
                    for (int col = 0; col < BOARD_SIZE; col++)
                    {
                        Brush brush = (row + col) % 2 == 0 ? whiteBrush : blackBrush;
                        e.Graphics.FillRectangle(brush, col * cellSize, row * cellSize, cellSize, cellSize);
                    }
                }
            }
        }
    }
}



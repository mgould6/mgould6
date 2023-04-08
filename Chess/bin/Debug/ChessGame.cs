using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;
using Chess;
using Chess.Properties;





namespace ChessGame
{
    public enum ChessPlayer
    {
        None,
        White,
        Black
    }

    public partial class ChessGame : Form
    {
        

        private const int BOARD_SIZE = 8;
        private const int PIECE_SIZE = 64;
        private const int BORDER_SIZE = 2;
        private ChessBoard chessBoard;
        private int squareSize;
        private ChessPlayer currentPlayer = ChessPlayer.White;


        private PictureBox[,] _pictureBoxes;
        private Point[,] _startingPositions;

        public ChessGame()
        {
            InitializeComponent();



            chessBoard = new ChessBoard();
            this.MouseDown += new MouseEventHandler(OnBoardClick);
            Initialize();

        }

        // Update the mouse click event handler to use the new classes
        // Update the mouse click event handler to use the new classes
        private void OnBoardClick(object sender, MouseEventArgs e)
        {
            int tileSize = 64; // Change this value according to your chessboard tile size

            int clickedColumn = e.X / tileSize;
            int clickedRow = e.Y / tileSize;

            // Ensure the clicked position is within the chessboard
            if (clickedColumn >= 0 && clickedColumn < 8 && clickedRow >= 0 && clickedRow < 8)
            {
                // Assuming you have a method to get the piece at the specified position
                ChessPiece clickedPiece = chessBoard.GetPieceAt(clickedColumn, clickedRow);
                if (clickedPiece != null)
                {
                    // Perform the desired action with the clicked piece
                    // e.g., select the piece, highlight valid moves, etc.
                    Console.WriteLine("Piece Clicked");
                }
            }
        }


        public void Initialize()
        {
            // Create chess board

            // Initialize _pictureBoxes array
            _pictureBoxes = new PictureBox[8, 8];

            // Set square size based on size of PictureBox controls
            squareSize = ClientSize.Width / 8;

            // Initialize starting positions
            _startingPositions = new Point[8, 8];
            for (int row = 0; row < 8; row++)
            {
                for (int col = 0; col < 8; col++)
                {
                    int adjustedRow = row;
                    int adjustedCol = col;

                    if (row >= 4)
                    {
                        adjustedRow = 7 - row;
                        adjustedCol = 7 - col;
                    }

                    _startingPositions[row, col] = new Point(adjustedCol * squareSize, adjustedRow * squareSize);
                }
            }

            // Set padding of table layout panel to zero
            tableLayoutPanel1.Padding = new Padding(0);

            // Add PictureBox controls to TableLayoutPanel
            for (int row = 0; row < 8; row++)
            {
                for (int col = 0; col < 8; col++)
                {
                    // Create PictureBox control and set properties
                    PictureBox pictureBox = new PictureBox();
                    pictureBox.SizeMode = PictureBoxSizeMode.StretchImage;
                    pictureBox.Width = squareSize;
                    pictureBox.Height = squareSize;
                    pictureBox.Tag = new BoardLocation(col, row);

                    // Set background color based on square color
                    if ((row + col) % 2 == 0)
                    {
                        pictureBox.BackColor = Color.White;
                    }
                    else
                    {
                        pictureBox.BackColor = Color.LightGray;
                    }

                    // Add PictureBox control to TableLayoutPanel
                    tableLayoutPanel1.Controls.Add(pictureBox, col, row);

                    // Save reference to PictureBox in array
                    _pictureBoxes[col, row] = pictureBox;

                    // Add event handler for mouse clicks
                    pictureBox.MouseClick += PictureBox_OnMouseClick;
                }
            }

            // Draw chessboard and chess pieces
            DrawChessBoard();
            DrawChessPieces();

        }






        public struct BoardLocation
        {
            public int Column { get; }
            public int Row { get; }

            public BoardLocation(int column, int row)
            {
                Column = column;
                Row = row;
            }
        }


        private void DrawChessBoard()
        {
            if (tableLayoutPanel1.RowCount != BOARD_SIZE || tableLayoutPanel1.ColumnCount != BOARD_SIZE)
            {
                throw new InvalidOperationException("The table layout panel does not have the expected number of rows and columns.");
            }

            for (int row = 0; row < BOARD_SIZE; row++)
            {
                for (int col = 0; col < BOARD_SIZE; col++)
                {
                    // Create a picture box
                    PictureBox pictureBox = new PictureBox();
                    pictureBox.Size = new Size(PIECE_SIZE, PIECE_SIZE);

                    if (tableLayoutPanel1.GetControlFromPosition(col, row) != null)
                    {
                        // The picture box already exists in the table layout panel, so update its properties
                        pictureBox = (PictureBox)tableLayoutPanel1.GetControlFromPosition(col, row);
                        pictureBox.Size = new Size(PIECE_SIZE, PIECE_SIZE);
                        pictureBox.BackColor = Color.Transparent;
                    }
                    else
                    {
                        // The picture box does not exist in the table layout panel, so add it and set its properties
                        pictureBox.Location = new Point(col * PIECE_SIZE, row * PIECE_SIZE);
                        pictureBox.BackColor = GetCellColor(row, col);
                        pictureBox.SizeMode = PictureBoxSizeMode.StretchImage;
                        pictureBox.BackColor = Color.Transparent; // Set background color to transparent

                        // Add picture box to table layout panel
                        tableLayoutPanel1.Controls.Add(pictureBox, col, row);
                    }

                    _pictureBoxes[row, col] = pictureBox;

                    // Attach OnMouseClick event to the picture box
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
                    ChessPiece piece = chessBoard.GetPieceAt(col, row);
                    PictureBox pictureBox = _pictureBoxes[col, row];

                    if (piece != null)
                    {
                        pictureBox.Image = GetChessPieceImage(row, col); // Get the image for the current piece
                    }
                    else
                    {
                        pictureBox.Image = null;
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

        private ChessPiece selectedPiece = null;
        private List<Move> validMoves = new List<Move>();

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>



        private void PictureBox_OnMouseClick(object sender, MouseEventArgs e)
        {
            // Get the clicked row and column
            int clickedColumn = e.X / squareSize;
            int clickedRow = e.Y / squareSize;

            // Get the chess piece at the clicked location
            ChessPiece clickedPiece = chessBoard.GetPieceAt(clickedRow, clickedColumn);

            if (selectedPiece == null)
            {
                // If no piece is selected, select the clicked piece if it belongs to the current player
                if (clickedPiece != null && clickedPiece.Player == currentPlayer)
                {
                    // Set the selected piece and get its valid moves
                    selectedPiece = clickedPiece;
                    validMoves = selectedPiece.GetValidMoves(chessBoard);

                    // Highlight the clicked square
                    _pictureBoxes[clickedRow, clickedColumn].BackColor = Color.LightBlue;

                    // Highlight valid destination squares
                    foreach (Move move in validMoves)
                    {
                        _pictureBoxes[move.ToRow, move.ToColumn].BackColor = Color.LightGreen;
                    }
                }
            }
            else
            {
                // Get the clicked destination square
                int destinationColumn = e.X / squareSize;
                int destinationRow = e.Y / squareSize;

                // Check if the clicked square is a valid destination
                Move validMove = validMoves.FirstOrDefault(move => move.ToRow == destinationRow && move.ToColumn == destinationColumn);

                if (validMove != null)
                {
                    // Move the piece on the chessboard
                    chessBoard.MovePiece(selectedPiece, destinationRow, destinationColumn);

                    // Toggle the current player's turn
                    currentPlayer = (currentPlayer == ChessPlayer.White) ? ChessPlayer.Black : ChessPlayer.White;

                    // Reset selectedPiece and validMoves
                    selectedPiece = null;
                    validMoves = null;

                    // Redraw the chessboard
                    DrawChessBoard();
                    DrawChessPieces();
                }
                else
                {
                    // Deselect the selected piece and clear the highlighted squares
                    _pictureBoxes[clickedRow, clickedColumn].BackColor = ((clickedRow + clickedColumn) % 2 == 0) ? Color.FromArgb(255, 235, 205) : Color.FromArgb(181, 136, 99);
                    foreach (Move move in validMoves)
                    {
                        _pictureBoxes[move.ToRow, move.ToColumn].BackColor = ((move.ToRow + move.ToColumn) % 2 == 0) ? Color.FromArgb(255, 235, 205) : Color.FromArgb(181, 136, 99);
                    }
                    selectedPiece = null;
                    validMoves = null;
                }
            }
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


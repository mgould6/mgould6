﻿using System;
using System.Drawing;
using System.Windows.Forms;
using Chess;
using Chess.Pieces;
using Chess.Enums;


namespace ChessGame
{
    public partial class ChessGame : Form
    {
        private const int BOARD_SIZE = 8;
        private const int PIECE_SIZE = 64;
        private const int BORDER_SIZE = 2;

        private PictureBox[,] _pictureBoxes;
        private Point[,] _startingPositions;
        private ChessPiece _selectedPiece;

        private readonly ChessBoard _chessBoard = new ChessBoard();
        private PlayerColor _currentPlayer;

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
                    // get image for chess piece
                    Image chessPieceImage = GetChessPieceImage(row, col);

                    // update image of picture box, if chess piece image is not null
                    if (chessPieceImage != null)
                    {
                        PictureBox pictureBox = _pictureBoxes[row, col];
                        pictureBox.Image = chessPieceImage;
                        pictureBox.SizeMode = PictureBoxSizeMode.CenterImage;
                        pictureBox.BackColor = Color.Transparent;
                        pictureBox.Anchor = AnchorStyles.None;

                        // center picture box within cell
                        int x = (PIECE_SIZE - chessPieceImage.Width) / 2;
                        int y = (PIECE_SIZE - chessPieceImage.Height) / 2;
                        pictureBox.Location = new Point(x, y);
                    }
                }
            }
        }



        private Image GetChessPieceImage(PlayerColor color, PieceType type)
        {
            string resourceName = $"{color}_{type}.png";
            return Properties.Resources.ResourceManager.GetObject(resourceName) as Image;
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



        private void PictureBox_OnMouseClick(object sender, MouseEventArgs e)
        {
            PictureBox pictureBox = sender as PictureBox;
            int row = tableLayoutPanel1.GetRow(pictureBox);
            int col = tableLayoutPanel1.GetColumn(pictureBox);
            ChessLocation clickedLocation = new ChessLocation(row, col);

            if (_selectedPiece == null)
            {
                // No piece currently selected, so select the clicked piece if it exists
                ChessPiece clickedPiece = _chessBoard.GetPieceAtLocation(clickedLocation);
                if (clickedPiece != null && clickedPiece.Color == _currentPlayer)
                {
                    _selectedPiece = clickedPiece;
                    _selectedPiece.Location = clickedLocation;
                    HighlightValidMoves(_selectedPiece);
                }
            }
            else
            {
                // A piece is currently selected, so move the piece if the clicked location is valid
                if (_selectedPiece.IsValidMove(clickedLocation))
                {
                    _selectedPiece.Move(clickedLocation);
                    _selectedPiece = null;
                    RemoveHighlights();
                    SwitchTurn();
                }
            }
        }

        private void UpdatePictureBoxes()
        {
            for (int row = 0; row < BOARD_SIZE; row++)
            {
                for (int col = 0; col < BOARD_SIZE; col++)
                {
                    // Get the piece at the current location
                    ChessPiece piece = _chessBoard.GetPieceAtLocation(new ChessLocation(row, col));

                    // Update the image of the picture box
                    if (piece != null)
                    {
                        _pictureBoxes[row, col].Image = GetChessPieceImage(piece.Color, piece.Type);
                    }
                    else
                    {
                        _pictureBoxes[row, col].Image = null;
                    }
                }
            }
        }

        private void EndGame(string message)
        {
            MessageBox.Show(message);
            _chessBoard.ResetBoard();
            UpdatePictureBoxes();
            _currentPlayer = PlayerColor.White;
        }

        private void SwitchTurn()
        {
            _currentPlayer = _currentPlayer == PlayerColor.White ? PlayerColor.Black : PlayerColor.White;
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


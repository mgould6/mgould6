﻿using Chess;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace ChessGame
{
    public partial class ChessGame : Form
    {
        private const int BOARD_SIZE = 8;
        private const int PIECE_SIZE = 64;
        private readonly Color lightSquareColor = Color.White;
        private readonly Color darkSquareColor = Color.Gray;
        private readonly Color defaultButtonColor = Color.Transparent;


        private PieceColor currentPlayerColor = PieceColor.White;
        private Board board;
        private PieceColor currentPlayer;
        private Piece selectedPiece;
        private Position selectedPiecePosition;



        public ChessGame()
        {
            InitializeComponent();
            Initialize();
            InitializeGameState();
            UpdateUI(); 
        }


        private void InitializeGameState()
        {
            board = new Board();
            board.InitializeBoard();
            currentPlayer = PieceColor.White;
            selectedPiece = null;
            selectedPiecePosition = null;
            UpdateUI();
        }
        private void UpdateUI()
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Button button = tableLayoutPanel1.GetControlFromPosition(j, i) as Button;
                    Piece piece = board.GetPiece(j, i);

                    if (piece != null)
                    {
                        button.BackgroundImage = piece.GetImage();
                    }
                    else
                    {
                        button.BackgroundImage = null;
                    }

                    // Set button background color
                    button.BackColor = (i + j) % 2 == 0 ? lightSquareColor : darkSquareColor;

                    // Highlight the selected piece
                    if (selectedPiecePosition != null && selectedPiecePosition.X == j && selectedPiecePosition.Y == i)
                    {
                        button.BackColor = Color.Yellow;
                    }
                }
            }
        }


        private void NextTurn()
        {
            currentPlayerColor = currentPlayerColor == PieceColor.White ? PieceColor.Black : PieceColor.White;
        }
        private void ClearSelection()
        {
            if (selectedPiecePosition != null)
            {
                tableLayoutPanel1.GetControlFromPosition(selectedPiecePosition.X, selectedPiecePosition.Y).BackColor = defaultButtonColor;
            }
            selectedPiece = null;
            selectedPiecePosition = null;
        }

        private void Button_Click(object sender, EventArgs e)
        {
            Button button = sender as Button;
            Position position = (Position)button.Tag;

            ClearSelection();

            if (selectedPiece == null)
            {
                // Select the piece if it belongs to the current player
                Piece clickedPiece = board.GetPiece(position.X, position.Y);
                if (clickedPiece != null && clickedPiece.Color == currentPlayer)
                {
                    selectedPiece = clickedPiece;
                    selectedPiecePosition = position;
                    UpdateUI(); // Highlight the selected piece
                }
            }
            else
            {
                // Try to move the selected piece to the clicked cell
                if (selectedPiece.IsValidMove(selectedPiecePosition, position, board))
                {
                    // Perform the move and update the game state
                    board.MovePiece(selectedPiecePosition, position);
                    selectedPiece = null;
                    selectedPiecePosition = null;
                    SwitchPlayer();
                }
                else
                {
                    // Deselect the piece
                    selectedPiece = null;
                    selectedPiecePosition = null;
                }
                UpdateUI(); // Refresh the UI
            }
        }

        private void SwitchPlayer()
        {
            currentPlayer = (currentPlayer == PieceColor.White) ? PieceColor.Black : PieceColor.White;
        }

        public Image GetChessPieceImage(Piece piece)
        {
            string pieceType = piece.GetType().Name;
            string imageName = pieceType + (piece.Color == PieceColor.White ? "_White" : "_Black");

            return (Image)Chess.Properties.Resources.ResourceManager.GetObject(imageName);
        }


        private void ClearHighlights()
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Button button = tableLayoutPanel1.GetControlFromPosition(j, i) as Button;
                    button.BackColor = (i + j) % 2 == 0 ? Color.White : Color.Gray;
                }
            }
        }

        public void Initialize()
        {
            

            // Set padding of table layout panel to zero
            tableLayoutPanel1.Padding = new Padding(0);

            // Draw chess board
            DrawChessBoard();

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
                    Button button = new Button();
                    button.Size = new Size(PIECE_SIZE, PIECE_SIZE);
                    button.Tag = new Position(col, row);
                    button.Click += Button_Click;

                    if ((row + col) % 2 == 0)
                    {
                        button.BackColor = Color.White;
                        button.FlatStyle = FlatStyle.Flat;
                        button.FlatAppearance.BorderSize = 0;

                    }
                    else
                    {
                        button.BackColor = Color.Gray;
                        button.FlatStyle = FlatStyle.Flat;
                        button.FlatAppearance.BorderSize = 0;

                    }
                    button.BackgroundImageLayout = ImageLayout.Center; // Add this line to center the images

                    tableLayoutPanel1.Controls.Add(button, col, row);
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


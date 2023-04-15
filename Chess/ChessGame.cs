using Chess;
using System;
using System.Drawing;
using System.Windows.Forms;

namespace ChessGame
{
    public partial class ChessGame : Form
    {
        private const int BOARD_SIZE = 8;
        private const int PIECE_SIZE = 64;

        private Point[,] _startingPositions;

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
            // Clear any highlights or error messages
            ClearHighlights();

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Button button = tableLayoutPanel1.GetControlFromPosition(j, i) as Button;
                    Position position = new Position(j, i);
                    Piece piece = board.GetPiece(position.X, position.Y);

                    if (piece != null)
                    {
                        // Set the button image to display the piece
                        button.BackgroundImage = GetChessPieceImage(piece);
                        button.BackgroundImageLayout = ImageLayout.Center; // Change from Stretch to Center
                        button.Text = string.Empty;
                    }
                    else
                    {
                        button.BackgroundImage = null;
                        button.Text = string.Empty;
                    }
                }
            }
        }

        private void NextTurn()
        {
            currentPlayerColor = currentPlayerColor == PieceColor.White ? PieceColor.Black : PieceColor.White;
        }
        private void Button_Click(object sender, EventArgs e)
        {
           Button button = sender as Button;
            Position position = (Position)button.Tag;

            if (selectedPiece == null)
            {
                // Select the piece if it belongs to the current player
                Piece clickedPiece = board.GetPiece(position.X, position.Y);
                if (clickedPiece != null && clickedPiece.Color == currentPlayer)
                {
                    selectedPiece = clickedPiece;
                    selectedPiecePosition = position;
                    button.BackColor = Color.Yellow; // Highlight the selected piece
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
                    UpdateUI();
                }
                else
                {
                    // Deselect the piece
                    selectedPiece = null;
                    selectedPiecePosition = null;
                    UpdateUI(); // Remove any highlights or error messages
                }
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


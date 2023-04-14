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
        private const int BORDER_SIZE = 2;

        private PictureBox[,] _pictureBoxes;
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
                        button.Image = GetChessPieceImage(piece);
                        button.Text = string.Empty;
                    }
                    else
                    {
                        button.Image = null;
                        button.Text = string.Empty;
                    }
                }
            }
        }

        private Image GetChessPieceImage(Piece piece)
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
                    }
                    else
                    {
                        button.BackColor = Color.Gray;
                    }

                    tableLayoutPanel1.Controls.Add(button, col, row);
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


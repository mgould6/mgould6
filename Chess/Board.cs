using System;

namespace Chess
{
    public class Board
    {
        public const int BOARD_SIZE = 8;
        private Piece[,] Pieces;

        public Board()
        {
            Pieces = new Piece[BOARD_SIZE, BOARD_SIZE];
        }

        public void InitializeBoard()
        {
            // Add code to initialize the board with the chess pieces.
            // For example:
            // Pieces[0, 0] = new Rook(PieceColor.White);
            // Pieces[0, 1] = new Knight(PieceColor.White);
            // ...
        }

        public Piece GetPiece(int x, int y)
        {
            if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
            {
                return Pieces[x, y];
            }
            return null;
        }

        public void SetPiece(int x, int y, Piece piece)
        {
            if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
            {
                Pieces[x, y] = piece;
            }
        }

        public bool IsPositionEmpty(int x, int y)
        {
            return GetPiece(x, y) == null;
        }

        public void MovePiece(Position from, Position to)
        {
            Piece pieceToMove = GetPiece(from.X, from.Y);
            if (pieceToMove != null)
            {
                SetPiece(from.X, from.Y, null);
                SetPiece(to.X, to.Y, pieceToMove);
            }
        }

        // Add other necessary methods
        // For example:
        // - A method to check if a move would put the king in check
        // - A method to check if a position is under attack by any opponent's pieces
    }
}

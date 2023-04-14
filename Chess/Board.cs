using System;
using Chess;


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
            // Initialize the board with empty spaces
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Pieces[i, j] = null;
                }
            }

            // Set up white pieces
            for (int i = 0; i < 8; i++)
            {
                Pieces[i, 1] = new Pawn(PieceColor.White);
            }
            Pieces[0, 0] = new Rook(PieceColor.White);
            Pieces[7, 0] = new Rook(PieceColor.White);
            Pieces[1, 0] = new Knight(PieceColor.White);
            Pieces[6, 0] = new Knight(PieceColor.White);
            Pieces[2, 0] = new Bishop(PieceColor.White);
            Pieces[5, 0] = new Bishop(PieceColor.White);
            Pieces[3, 0] = new Queen(PieceColor.White);
            Pieces[4, 0] = new King(PieceColor.White);

            // Set up black pieces
            for (int i = 0; i < 8; i++)
            {
                Pieces[i, 6] = new Pawn(PieceColor.Black);
            }
            Pieces[0, 7] = new Rook(PieceColor.Black);
            Pieces[7, 7] = new Rook(PieceColor.Black);
            Pieces[1, 7] = new Knight(PieceColor.Black);
            Pieces[6, 7] = new Knight(PieceColor.Black);
            Pieces[2, 7] = new Bishop(PieceColor.Black);
            Pieces[5, 7] = new Bishop(PieceColor.Black);
            Pieces[3, 7] = new Queen(PieceColor.Black);
            Pieces[4, 7] = new King(PieceColor.Black);
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

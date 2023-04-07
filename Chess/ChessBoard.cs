using ChessGame;
using System;
using Chess;
using .


namespace Chess
{
    public class ChessBoard
    {
        private const int BOARD_SIZE = 8;
        private ChessPiece[,] _pieces;

        public ChessBoard()
        {
            _pieces = new ChessPiece[BOARD_SIZE, BOARD_SIZE];
        }

        public void AddPiece(ChessPiece piece, int row, int col)
        {
            if (IsValidPosition(row, col))
            {
                _pieces[row, col] = piece;
                piece.ChessBoard = this;
                piece.Location = new ChessLocation(row, col);
            }
            else
            {
                throw new ArgumentException("Invalid position");
            }
        }

        public void RemovePiece(int row, int col)
        {
            if (IsValidPosition(row, col))
            {
                _pieces[row, col] = null;
            }
            else
            {
                throw new ArgumentException("Invalid position");
            }
        }

        public ChessPiece GetPieceAtLocation(ChessLocation location)
        {
            if (IsValidPosition(location.Row, location.Col))
            {
                return _pieces[location.Row, location.Col];
            }
            else
            {
                throw new ArgumentException("Invalid position");
            }
        }

        private bool IsValidPosition(int row, int col)
        {
            return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
        }

        public static void HighlightTile(int row, int col)
        {
            // TODO: Implement tile highlighting
        }

        public static void RemoveHighlight(int row, int col)
        {
            // TODO: Implement tile highlighting removal
        }
    }
}

using Chess;
using System;

namespace Chess
{
    public class Pawn : Piece
    {

        public Pawn(PieceColor color) : base(color)
        {
        }

        public override bool IsValidMove(Position from, Position to, Board board)
        {
            int direction = Color == PieceColor.White ? 1 : -1;
            int deltaX = to.X - from.X;
            int deltaY = to.Y - from.Y;

            if (deltaX == 0 && deltaY == direction)
            {
                return board.GetPiece(to.X, to.Y) == null;
            }
            else if (Math.Abs(deltaX) == 1 && deltaY == direction)
            {
                Piece targetPiece = board.GetPiece(to.X, to.Y);
                return targetPiece != null && targetPiece.Color != this.Color;
            }
            else if (deltaY == 2 * direction && from.Y == (Color == PieceColor.White ? 1 : 6))
            {
                return deltaX == 0
                    && board.GetPiece(from.X, from.Y + direction) == null
                    && board.GetPiece(to.X, to.Y) == null;
            }

            return false;
        }
    }
}

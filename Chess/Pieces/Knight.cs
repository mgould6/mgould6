using Chess;
using System;

namespace Chess
{
    public class Knight : Piece
    {
        public Knight(PieceColor color) : base(color)
        {
        }

        public override bool IsValidMove(Position from, Position to, Board board)
        {
            int deltaX = Math.Abs(to.X - from.X);
            int deltaY = Math.Abs(to.Y - from.Y);

            if ((deltaX == 1 && deltaY == 2) || (deltaX == 2 && deltaY == 1))
            {
                Piece targetPiece = board.GetPiece(to.X, to.Y);
                return targetPiece == null || targetPiece.Color != this.Color;
            }

            return false;
        }
    }
}

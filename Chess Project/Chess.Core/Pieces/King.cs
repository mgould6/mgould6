using Chess.Core;
using System;

namespace Chess.Core
{
    public class King : Piece
    {
        public King(PieceColor color) : base(color)
        {
        }

        public override bool IsValidMove(Position from, Position to, Board board)
        {
            int deltaX = Math.Abs(to.X - from.X);
            int deltaY = Math.Abs(to.Y - from.Y);

            if (deltaX <= 1 && deltaY <= 1)
            {
                Piece targetPiece = board.GetPiece(to.X, to.Y);
                return targetPiece == null || targetPiece.Color != this.Color;
            }

            return false;
        }
    }
}

using Chess.Core;
using System;

namespace Chess.Core
{
    public class Bishop : Piece
    {
        public Bishop(PieceColor color) : base(color)
        {
        }

        public override bool IsValidMove(Position from, Position to, Board board)
        {
            int deltaX = Math.Abs(to.X - from.X);
            int deltaY = Math.Abs(to.Y - from.Y);

            if (deltaX == deltaY)
            {
                int stepX = (to.X - from.X) / deltaX;
                int stepY = (to.Y - from.Y) / deltaY;

                int currentX = from.X + stepX;
                int currentY = from.Y + stepY;

                while (currentX != to.X || currentY != to.Y)
                {
                    if (board.GetPiece(currentX, currentY) != null)
                    {
                        return false;
                    }

                    currentX += stepX;
                    currentY += stepY;
                }

                Piece targetPiece = board.GetPiece(to.X, to.Y);
                return targetPiece == null || targetPiece.Color != this.Color;
            }

            return false;
        }
    }
}

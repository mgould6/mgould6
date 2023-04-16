using Chess.Core;
using System;

namespace Chess.Core
{
    public class Queen : Piece
    {
        public Queen(PieceColor color) : base(color)
        {
        }

        public override bool IsValidMove(Position from, Position to, Board board)
        {
            int deltaX = Math.Abs(to.X - from.X);
            int deltaY = Math.Abs(to.Y - from.Y);

            // Check if the move is in a straight line (horizontal, vertical) or diagonal
            if (deltaX == 0 || deltaY == 0 || deltaX == deltaY)
            {
                // Ensure there are no other pieces between the source and destination positions
                int stepX = (to.X - from.X) == 0 ? 0 : (to.X - from.X) / Math.Abs(to.X - from.X);
                int stepY = (to.Y - from.Y) == 0 ? 0 : (to.Y - from.Y) / Math.Abs(to.Y - from.Y);

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

                // Ensure the destination position is empty or contains an opponent's piece
                Piece targetPiece = board.GetPiece(to.X, to.Y);
                return targetPiece == null || targetPiece.Color != this.Color;
            }

            return false;
        }
    }
}

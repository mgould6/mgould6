using Chess;
using System.Drawing;

namespace Chess
{
    public abstract class Piece
    {
        public PieceColor Color { get; }

        public Piece(PieceColor color)
        {
            Color = color;
        }

        public Image GetImage()
        {
            return GetChessPieceImage(this);
        }

        public abstract bool IsValidMove(Position from, Position to, Board board);

        public Image GetChessPieceImage(Piece piece)
        {
            string pieceType = piece.GetType().Name;
            string imageName = pieceType + (piece.Color == PieceColor.White ? "_White" : "_Black");

            return (Image)Chess.Properties.Resources.ResourceManager.GetObject(imageName);
        }
    }
}

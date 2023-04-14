using Chess;


namespace Chess
{
    public abstract class Piece
    {
        public PieceColor Color { get; }

        public Piece(PieceColor color)
        {
            Color = color;
        }

        public abstract bool IsValidMove(Position from, Position to, Board board);
    }
}

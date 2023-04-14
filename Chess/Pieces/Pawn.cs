using Chess;

namespace Chess
{
    public class Pawn : Piece
    {
        private bool _hasMoved;

        public Pawn(PieceColor color) : base(color)
        {
            _hasMoved = false;
        }

        public override bool IsValidMove(Position from, Position to, Board board)
        {
            // Implement your pawn movement logic here
            return true;
        }
    }
}

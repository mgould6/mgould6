using Chess;
using Xunit;

namespace Chess.Core
{
    public class BoardTests
    {
        private readonly Board _board;

        public BoardTests()
        {
            _board = new Board();
            _board.InitializeBoard();
        }

        [Fact]
        public void BoardIsInitializedCorrectly()
        {
            // Test the initial setup for white pieces
            Assert.IsType<Rook>(_board.GetPiece(0, 0));
            Assert.IsType<Knight>(_board.GetPiece(1, 0));
            Assert.IsType<Bishop>(_board.GetPiece(2, 0));
            Assert.IsType<Queen>(_board.GetPiece(3, 0));
            Assert.IsType<King>(_board.GetPiece(4, 0));
            Assert.IsType<Bishop>(_board.GetPiece(5, 0));
            Assert.IsType<Knight>(_board.GetPiece(6, 0));
            Assert.IsType<Rook>(_board.GetPiece(7, 0));

            for (int i = 0; i < 8; i++)
            {
                Assert.IsType<Pawn>(_board.GetPiece(i, 1));
            }

            // Test the initial setup for black pieces
            Assert.IsType<Rook>(_board.GetPiece(0, 7));
            Assert.IsType<Knight>(_board.GetPiece(1, 7));
            Assert.IsType<Bishop>(_board.GetPiece(2, 7));
            Assert.IsType<Queen>(_board.GetPiece(3, 7));
            Assert.IsType<King>(_board.GetPiece(4, 7));
            Assert.IsType<Bishop>(_board.GetPiece(5, 7));
            Assert.IsType<Knight>(_board.GetPiece(6, 7));
            Assert.IsType<Rook>(_board.GetPiece(7, 7));

            for (int i = 0; i < 8; i++)
            {
                Assert.IsType<Pawn>(_board.GetPiece(i, 6));
            }

            // Test that the middle of the board is empty
            for (int i = 2; i < 6; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Assert.Null(_board.GetPiece(j, i));
                }
            }
        }
    }
}

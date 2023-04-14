using Chess;
using Xunit;

namespace Chess.Tests
{
    public class RookTests
    {
        [Fact]
        public void Rook_CanMoveHorizontally()
        {
            // Arrange
            var board = new Board();
            var rook = new Rook(PieceColor.White);
            var from = new Position(0, 0); // Assuming 0-based indexing
            var to = new Position(4, 0);

            // Act
            bool isValidMove = rook.IsValidMove(from, to, board);

            // Assert
            Assert.True(isValidMove);
        }

        // Add more test methods for other rook movement scenarios
    }
}

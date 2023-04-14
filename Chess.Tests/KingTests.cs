using Chess;
using Xunit;

namespace Chess.Tests
{
    public class KingTests
    {
        [Fact]
        public void King_CanMoveOneSpaceDiagonally()
        {
            // Arrange
            var board = new Board();
            var king = new King(PieceColor.White);
            var from = new Position(4, 0); // Assuming 0-based indexing
            var to = new Position(5, 1);

            // Act
            bool isValidMove = king.IsValidMove(from, to, board);

            // Assert
            Assert.True(isValidMove);
        }

        // Add more test methods for other king movement scenarios
    }
}

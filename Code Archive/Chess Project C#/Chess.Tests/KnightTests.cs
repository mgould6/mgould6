using Chess;
using Xunit;

namespace Chess.Core
{
    public class KnightTests
    {
        [Fact]
        public void Knight_CanMoveInLShape()
        {
            // Arrange
            var board = new Board();
            var knight = new Knight(PieceColor.White);
            var from = new Position(1, 0); // Assuming 0-based indexing
            var to = new Position(0, 2);

            // Act
            bool isValidMove = knight.IsValidMove(from, to, board);

            // Assert
            Assert.True(isValidMove);
        }

        // Add more test methods for other knight movement scenarios
    }
}

using Chess;
using Xunit;

namespace Chess.Tests
{
    public class QueenTests
    {
        [Fact]
        public void Queen_CanMoveDiagonally()
        {
            // Arrange
            var board = new Board();
            var queen = new Queen(PieceColor.White);
            var from = new Position(3, 0); // Assuming 0-based indexing
            var to = new Position(6, 3);

            // Act
            bool isValidMove = queen.IsValidMove(from, to, board);

            // Assert
            Assert.True(isValidMove);
        }

        // Add more test methods for other queen movement scenarios
    }
}

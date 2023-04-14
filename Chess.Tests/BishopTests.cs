using Chess;
using Xunit;

namespace Chess.Tests
{
    public class BishopTests
    {
        [Fact]
        public void Bishop_CanMoveDiagonally()
        {
            // Arrange
            var board = new Board();
            var bishop = new Bishop(PieceColor.White);
            var from = new Position(2, 0); // Assuming 0-based indexing
            var to = new Position(5, 3);

            // Act
            bool isValidMove = bishop.IsValidMove(from, to, board);

            // Assert
            Assert.True(isValidMove);
        }

        // Add more test methods for other bishop movement scenarios
    }
}

using Chess.Core;
using Xunit;

namespace Chess.Tests
{
    public class PawnTests
    {
        [Fact]
        public void Pawn_CanMoveForward_TwoSpaces_WhenNotMoved()
        {
            // Arrange
            var board = new Board();
            var pawn = new Pawn(PieceColor.White);
            var from = new Position(1, 2); // Assuming 0-based indexing
            var to = new Position(1, 4);

            // Act
            bool isValidMove = pawn.IsValidMove(from, to, board);

            // Assert
            Assert.True(isValidMove);
        }

        // Add more test methods for other pawn movement scenarios
    }
}

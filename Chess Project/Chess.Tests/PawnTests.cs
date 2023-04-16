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
            board.InitializeBoard(); // Initialize the board
            var pawn = new Pawn(PieceColor.White);
            var from = new Position(1, 1); // Assuming 0-based indexing, initial pawn position
            var to = new Position(1, 3);

            // Set the pawn on the board
            board.SetPiece(from.X, from.Y, pawn);

            // Act
            bool isValidMove = pawn.IsValidMove(from, to, board);

            // Assert
            Assert.True(isValidMove);
        }

        // Add more test methods for other pawn movement scenarios
    }
}

using System.Collections.Generic;
using Chess;

public class Bishop : ChessPiece
{
    public Bishop(int column, int row, bool isWhite) : base(column, row, isWhite)
    {
    }

    public override List<Move> GetValidMoves(ChessBoard board)
    {
        List<Move> validMoves = new List<Move>();

        // Check moves in each diagonal direction
        int[] directions = { -1, 1 };
        foreach (int dColumn in directions)
        {
            foreach (int dRow in directions)
            {
                for (int distance = 1; distance <= 7; distance++)
                {
                    int newColumn = Column + (dColumn * distance);
                    int newRow = Row + (dRow * distance);
                    ChessPiece targetPiece = board.GetPieceAt(newColumn, newRow);
                    if (targetPiece == null)
                    {
                        validMoves.Add(new Move(this, Column, Row, newColumn, newRow));
                    }
                    else
                    {
                        if (targetPiece.IsWhite != IsWhite)
                        {
                            validMoves.Add(new Move(this, Column, Row, newColumn, newRow));
                        }
                        break;
                    }
                }
            }
        }

        return validMoves;
    }

}
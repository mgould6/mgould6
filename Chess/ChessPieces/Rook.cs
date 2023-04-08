using System.Collections.Generic;
using Chess;
using Chess.Properties;
using System.Drawing;

public class Rook : ChessPiece
{
    public Rook(int column, int row, bool isWhite) : base(column, row, isWhite)
    {
    }

    public override List<Move> GetValidMoves(ChessBoard board)
    {
        List<Move> validMoves = new List<Move>();

        // Check moves in each direction (horizontal and vertical)
        int[] directions = { -1, 1 };
        foreach (int dColumn in directions)
        {
            for (int distance = 1; distance <= 7; distance++)
            {
                int newColumn = Column + (dColumn * distance);
                ChessPiece targetPiece = board.GetPieceAt(newColumn, Row);
                if (targetPiece == null)
                {
                    validMoves.Add(new Move(this, Column, Row, newColumn, Row));
                }
                else
                {
                    if (targetPiece.IsWhite != IsWhite)
                    {
                        validMoves.Add(new Move(this, Column, Row, newColumn, Row));
                    }
                    break;
                }
            }
        }

        // Repeat the same logic for vertical moves (changing dRow instead of dColumn)

        return validMoves;
    }
    public override Image Image
    {
        get { return ImageProvider.GetImageForPiece(this); }
    }

}
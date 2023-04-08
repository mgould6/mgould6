using ChessGame;
using System.Collections.Generic;
using Chess;
using System.Drawing;


public abstract class ChessPiece
{

    public ChessPlayer Player { get; set; }

    public int Column { get; set; }
    public int Row { get; set; }
    public bool IsWhite { get; set; }

    public ChessPiece(int column, int row, bool isWhite)
    {
        Column = column;
        Row = row;
        IsWhite = isWhite;
    }
    public ChessPiece(ChessPlayer player)
    {
        Player = player;
    }

    public abstract Image Image { get; }

    public abstract List<Move> GetValidMoves(ChessBoard board);

}
using ChessGame;
using System;
using Chess;
using System.Collections.Generic;

public enum PieceType
{
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
}

public enum PlayerColor
{
    White,
    Black
}

public abstract class ChessPiece
{
    public PieceType Type { get; set; }
    public PlayerColor Color { get; set; }
    public ChessLocation Location { get; set; }
    public abstract List<ChessLocation> GetValidMoves();


    public ChessPiece(PieceType type, PlayerColor color, ChessLocation location)
    {
        Type = type;
        Color = color;
        Location = location;
    }

    public void HighlightValidMoves()
    {
        foreach (var move in GetValidMoves())
        {
            ChessBoard.HighlightTile(move.Row, move.Col);
        }
    }

    public void RemoveHighlights()
    {
        foreach (var move in GetValidMoves())
        {
            ChessBoard.RemoveHighlight(move.Row, move.Col);
        }
    }


    public bool IsValidMove(ChessLocation destination)
    {
        // TODO: Implement this method to check if the move is valid for the piece
        throw new NotImplementedException();
    }

    public void Move(ChessLocation destination)
    {
        // TODO: Implement this method to move the piece to the destination location
        throw new NotImplementedException();
    }


}

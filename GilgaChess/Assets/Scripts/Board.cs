using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Board : MonoBehaviour
{
    private List<Piece> pieces = new List<Piece>();

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public List<Piece> GetAllPieces()
    {
        // Return a list of all pieces on the board
        return pieces;
    }

    public void SetPieces(List<Piece> initialPieces)
    {
        pieces = initialPieces;
    }

    public void AddPiece(Piece piece)
    {
        // Add the given piece to the board
        pieces.Add(piece);
    }

    public void RemovePiece(Piece piece)
    {
        // Remove the given piece from the board
        pieces.Remove(piece);
    }


}

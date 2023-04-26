using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoardGenerator : MonoBehaviour
{
    public GameObject tilePrefab;
    public int boardSize = 8;
    public GameObject lightTilePrefab;
    public GameObject darkTilePrefab;
    public Board board;



    void Start()
    {
        GenerateBoard();
    }

    private void GenerateBoard()
    {
        List<Piece> generatedPieces = new List<Piece>();

        for (int x = 0; x < boardSize; x++)
        {
            for (int y = 0; y < boardSize; y++)
            {
                GameObject tilePrefab = (x + y) % 2 == 0 ? lightTilePrefab : darkTilePrefab;
                Vector3 position = new Vector3(x, y, 0);
                GameObject tile = Instantiate(tilePrefab, position, Quaternion.identity);
                tile.transform.SetParent(transform);

                Vector2Int position2D = new Vector2Int(x, y);
                GameObject piecePrefab = GetPiecePrefab(position2D);
                if (piecePrefab != null)
                {
                    GameObject piece = Instantiate(piecePrefab, position, Quaternion.identity);
                    piece.transform.SetParent(tile.transform);

                    Piece pieceComponent = piece.GetComponent<Piece>();
                    if (pieceComponent != null)
                    {
                        generatedPieces.Add(pieceComponent);
                    }
                }
            }
        }

        // Set the generated pieces in the Board class
        board.SetPieces(generatedPieces);
    }




    private GameObject GetPiecePrefab(Vector2Int position)
    {
        Dictionary<Vector2Int, string> startingPositions = new Dictionary<Vector2Int, string>
    {
        { new Vector2Int(0, 0), "RookWhite" },
        { new Vector2Int(1, 0), "KnightWhite" },
        { new Vector2Int(2, 0), "BishopWhite" },
        { new Vector2Int(3, 0), "QueenWhite" },
        { new Vector2Int(4, 0), "KingWhite" },
        { new Vector2Int(5, 0), "BishopWhite" },
        { new Vector2Int(6, 0), "KnightWhite" },
        { new Vector2Int(7, 0), "RookWhite" },

        { new Vector2Int(0, 7), "RookBlack" },
        { new Vector2Int(1, 7), "KnightBlack" },
        { new Vector2Int(2, 7), "BishopBlack" },
        { new Vector2Int(3, 7), "QueenBlack" },
        { new Vector2Int(4, 7), "KingBlack" },
        { new Vector2Int(5, 7), "BishopBlack" },
        { new Vector2Int(6, 7), "KnightBlack" },
        { new Vector2Int(7, 7), "RookBlack" }
    };

        for (int i = 0; i < 8; i++)
        {
            startingPositions[new Vector2Int(i, 1)] = "PawnWhite";
            startingPositions[new Vector2Int(i, 6)] = "PawnBlack";
        }

        if (startingPositions.ContainsKey(position))
        {
            string prefabName = startingPositions[position];
            GameObject prefab = Resources.Load<GameObject>(prefabName);
            return prefab;
        }
        else
        {
            return null;
        }
    }

}

## Basic Shape Detection from an Image

Algorithmic Overview:
    
    Step 1: Include all neccessary libraries and read the image. 

    Step 2: Convert the image into grayscale to simplify the shape detection process. 

    Step 3: Contour Processing
        3a: Draw contours and find out the number of contours draw for each shape. 
        3b: Calculate the centroid in order place the text appropriately. 

    Step 4: Identification of the shape 
        4a: TRIANGLE IDENTIFICATION
            -- Triangles have three vertice; if the approximation has three vertices it's likely a triangle. 
        
        4b: SQUARE & RECTANGLE IDENTIFICATION
            -- Both squares and rectangles have four vertices. 
            -- Calculated based on their aspect ratio 
            -- If aspect ratio is close to 1, it is considered a square; else it is considered as a rectangle, 

        4c: TRAPEZIUM IDENTIFICATION
            -- Trapeziums have four vertices. 
            -- Trapeziums are neither a square nor a rectangle but has nearly equal opposite sides. 
            -- Calculated by comparing the length of the opposite sides. 
            -- If opposite sides are not of equal length then it is a trapezium. 
        
        4d: PENTAGON IDENTIFICATION
            -- Pentagons have five vertices. 
            -- If approximation has five vertices, it is then identified as a pentagon. 
        
        4e: HEXAGON IDENTIFICATION
            -- Hexagons have six vertices. 
            -- If the approximation have six vertices, it is then identified as a hexagon. 

        4f: OCTAGON IDENTIFICATION
            -- Identified basis the side lengths using the Euclidean's distance.
            -- Length of the side is computed via the Euclidean Distance between the consecutive vertices. 
            -- If all the side lengths are roughly equal the shape is considered as an octagon. 
            -- If not, then it is considered as a rectangle (Use Case: Rectangles with curved surface edges).
            -- If the absolute difference between any side length and the first length exceeds the threshold, then it is a rectangle. 
            -- If it does not exceed the limit then it is an octagon. 

        4g: CIRCLE & ELLIPSE IDENTIFICATION
            -- Circles and ellipses are calculated basis their aspect ratio. 
            -- If the ratio of the minimum to maximum diameter is very close to 1, it is considered as a circle. 
            -- If the ratio is not close to 1, it is then called as an ellipse. 

    Step 4: Displaying the result over the annotated shapes. 
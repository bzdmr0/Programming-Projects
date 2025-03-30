function A3_2584738(Image)

    segmentedIm = Segmentation(Image);

    num = counting(segmentedIm);
    
    figure;
    imshow(segmentedIm);title(num);

    function segmentedIm = Segmentation(Image)

        %thresholding based on yellow color.
        yellow_mask = Image(:,:,1) > 220 & Image(:,:,2) > 150 & Image(:,:,3) < 80;
        
        %morphological opening and closing.
        %used different size of structing elements for closing opening to find
        %ideal one.
        SE_forClose= strel("disk",15);
        SE_forOpen = strel("disk",20);
        %closed to connect the yellowish pixels of eggs.
        closedIm = imclose(yellow_mask,SE_forClose);
        %opend to eliminate other yellowish pixels.
        openedIm = imopen(closedIm,SE_forOpen);
        %filled the holes inside eggs.
        openedIm = imfill(openedIm,"holes");
        %erode for eggs which are very close each other
        %it changes shapes but we know each seperate element is an egg.
        SE = strel("disk",20);
        segmentedIm= imerode(openedIm,SE); 
        
        figure;
        subplot(1,3,1);
        imshow(yellow_mask);title("Segmentation based on intensity");
        subplot(1,3,2);
        imshow(closedIm);title("Closing of segmented image");
        subplot(1,3,3);
        imshow(openedIm);title("Opening of segmented image after closing");
        
        return
    end


    function numEggs = counting(segmentedIm)

        %counting half eggs with connected component extraction method
        C =  bwconncomp(segmentedIm,18);
        numOfHalfEggs = size(C.PixelIdxList,2);
        %finding eggs number from pairs of halves of eggs
        numEggs = numOfHalfEggs/2;
        
        return
    end
end
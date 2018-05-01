% Matlab file to generate rate distorstion graph.

image_precision = 100;
font_size = 16;
line_width = 3;

plot(bpv, l2_error, 'k', 'LineWidth',line_width);
title_caption = sprintf('Distortion (image %s)',test_name);
title(title_caption, 'FontWeight','bold', 'FontSize', font_size);
xlabel('Bits per vertex.', 'FontSize', font_size-2)
ylabel('L2 error.', 'FontSize', font_size-2);

PSNR = 20*log10( 255*255./l2_error );

file_name = sprintf('%s%s','Distortion_',test_name);
str = sprintf('print -dpng -r%d %s', image_precision, file_name);
eval(str);	% save the image in a png graphic


plot(bpv, PSNR, 'k', 'LineWidth',line_width);
title_caption = sprintf('PSNR (image %s)',test_name);
title(title_caption, 'FontWeight','bold', 'FontSize', font_size);
xlabel('Bits per vertex', 'FontSize', font_size-2)
ylabel('dB', 'FontSize', font_size-2);

file_name = sprintf('%s%s','PSNR_',test_name);
str = sprintf('print -dpng -r%d %s', image_precision, file_name);
eval(str);	% save the image in a png graphic


/*printf("%d %d\n", menu.N, menu.M);
	for (int i = 0; i < menu.N; i++)printf("%s ", menu.food[i].name);
	printf("\n");
	for (int i = 0; i < menu.N; i++)printf("%d ", menu.food[i].time);
	printf("\n");
	for (int i = 0; i < menu.N; i++)printf("%d ", menu.food[i].capacity);
	printf("\n%d %d\n", menu.W1, menu.W2);
	for (int i = 0; i < menu.M; i++) {
		printf("%s ", menu.combo[i].name);
		int cnt = 0;
		while (1)
		{
			if (strcmp(menu.combo[i].food[cnt].name, "") == 0)break;
			else printf("%s ", menu.combo[i].food[cnt++].name);
		}
		printf("\n");
	}*/
//|| ((order <= menu.W1 && order >= menu.W2) && open == 0)